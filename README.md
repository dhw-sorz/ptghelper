# README
¡¡¡THIS IS A GENTOO ONLY TOOL!!!

Unmask is a simple tool written in C to unmask packages automatically without having to edit files.
This tool will only work if your system organizes /package.accept_keywords as a directory and not a single file.

DEPENDENCIES

The only dependency for this program is the GNU COMPILER COLLECTION (gcc), and gentoo linux, THIS WILL NOT WORK IN ANY OTHER DISTRO, AND IS NOT TESTED IN OTHER GENTOO BASED DISTROS

INSTALLATION

Clone the repository using git:
git clone https://github.com/dhw-sorz/Unmask.git

Enter the directory:
cd unmask

Compile and install:
make
sudo make install

HOW TO USE

unmask <package you're trying to compile> <dependency to unmask> <keyword>(if unspecified will use your CPU architecture)

Example:

Firefox needs sys-devel/clang to compile, but the package is masked, you run
unmask firefox sys-devel/clang (we will assume you use amd64 architecture)

This command will write "sys-devel/clang ~amd64" to /package.accept_keywords/firefox

I hope you enjoy my tool ^.^
