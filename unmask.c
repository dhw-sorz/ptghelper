#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (strcmp(argv[1], "--version") == 0) {
		printf("Literally the first version\n");
		return 0;
	}
	if (geteuid() != 0) {
		fprintf(stderr, "This program must be run as root\n");
		return 1;
	}

	if (argc < 3) {
		fprintf(stderr, "Usage: unmask <package> <dependency to unmask>\n");
		return 1;
	}

	const char *arch_env = getenv("ARCH");

	char keyword[64];
	if (argc >= 4) {
		snprintf(keyword, sizeof(keyword), "%s", argv[3]);
	} else if (arch_env != NULL) {
		snprintf(keyword, sizeof(keyword), "~%s", arch_env);
	} else {
		snprintf(keyword, sizeof(keyword), "~amd64");
	}

	char path[512];
	snprintf(path, sizeof(path), "/etc/portage/package.accept_keywords/%s", argv[1]);

	FILE *check = fopen(path, "r");
	if (check != NULL) {
		char line[256];
		while (fgets(line, sizeof(line), check)) {
			if (strstr(line, argv[2])) {
				printf("'%s' is already unmasked for '%s'\n", argv[2], argv[1]);
				fclose(check);
				return 0;
			}
		}
		fclose(check);
	}

	FILE *fp = fopen(path, "a");
	if (fp == NULL) {
		perror("Error opening file");
		return 1;
	}

	fprintf(fp, "%s %s\n", argv[2], keyword);
	fclose(fp);

	printf("Unmasked %s for %s (keyword: %s)\n", argv[2], argv[1], keyword);
	return 0;
}
