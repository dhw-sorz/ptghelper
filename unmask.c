#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int cmd_unmask(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: ptghelper unmask <package> <dependency>\n");
        return 1;
    }

    const char *arch_env = getenv("ARCH");
    char keyword[64];
    if (argc >= 5) {
        snprintf(keyword, sizeof(keyword), "%s", argv[4]);
    } else if (arch_env != NULL) {
        snprintf(keyword, sizeof(keyword), "~%s", arch_env);
    } else {
        snprintf(keyword, sizeof(keyword), "~amd64");
    }

    char path[512];
    snprintf(path, sizeof(path), "/etc/portage/package.accept_keywords/%s", argv[2]);

    FILE *check = fopen(path, "r");
    if (check != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), check)) {
            if (strstr(line, argv[3])) {
                printf("'%s' is already unmasked for '%s'\n", argv[3], argv[2]);
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

    fprintf(fp, "%s %s\n", argv[3], keyword);
    fclose(fp);

    printf("Unmasked %s for %s (keyword: %s)\n", argv[3], argv[2], keyword);
    return 0;
}

int cmd_acp_lic(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: ptghelper acp-lic <dependency> <license>\n");
        return 1;
    }

    FILE *check = fopen("/etc/portage/package.license", "r");
    if (check != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), check)) {
            if (strstr(line, argv[2])) {
                printf("'%s' already has an accepted license.\n", argv[2]);
                fclose(check);
                return 0;
            }
        }
        fclose(check);
    }

    FILE *fp = fopen("/etc/portage/package.license", "a");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(fp, "%s %s\n", argv[2], argv[3]);
    fclose(fp);

    printf("Accepted license %s for %s\n", argv[3], argv[2]);
    return 0;
}

int cmd_chuse(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, "Usage: ptghelper chuse <package> <dependency> <useflag>\n");
        return 1;
    }

    char path[512];
    snprintf(path, sizeof(path), "/etc/portage/package.use/%s", argv[2]);

    FILE *check = fopen(path, "r");
    if (check != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), check)) {
            if (strstr(line, argv[3])) {
                printf("'%s' already has a use flag entry in '%s'\n", argv[3], argv[2]);
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

    fprintf(fp, "%s %s\n", argv[3], argv[4]);
    fclose(fp);

    printf("Set use flag %s for %s in %s\n", argv[4], argv[3], argv[2]);
    return 0;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: ptghelper <subcommand> [args]\n");
        fprintf(stderr, "Subcommands: unmask, acp-lic, chuse\n");
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0) {
        printf("ptghelper - literally the first version\n");
        return 0;
    }

    if (geteuid() != 0) {
        fprintf(stderr, "Error: this program must be run as root.\n");
        return 1;
    }

    if (strcmp(argv[1], "unmask") == 0) {
        return cmd_unmask(argc, argv);
    } else if (strcmp(argv[1], "acp-lic") == 0) {
        return cmd_acp_lic(argc, argv);
    } else if (strcmp(argv[1], "chuse") == 0) {
        return cmd_chuse(argc, argv);
    } else {
        fprintf(stderr, "Unknown subcommand: %s\n", argv[1]);
        fprintf(stderr, "Subcommands: unmask, acp-lic, chuse\n");
        return 1;
    }
}
