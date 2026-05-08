# README
¡¡¡THIS IS A GENTOO ONLY TOOL!!!

ptghelper is a simple tool written in C to help save time with the portage packet manager, it can unmask files, change use flags per package and accept licenses. 

DEPENDENCIES

The only dependency for this program is the GNU COMPILER COLLECTION (gcc), and gentoo linux, THIS WILL NOT WORK IN ANY OTHER DISTRO, AND IS NOT TESTED IN OTHER GENTOO BASED DISTROS

INSTALLATION

Clone the repository using git:

git clone https://github.com/dhw-sorz/ptghelper.git

Enter the directory:

cd ~/unmask

Compile and install:

make

sudo make install

HOW TO USE

Unmask:

ptghelper unmask <package you're trying to compile> <dependency to unmask> <keyword>(if unspecified will use your CPU architecture)

Example:

Firefox needs sys-devel/clang to compile, but the package is masked, you run
ptghelper unmask firefox sys-devel/clang (we will assume you use amd64 architecture)

Chuse:

ptghelper chuse <package you're trying to install> <dependency that needs use flag change> <use flag>

Example:

Spotify needs dev-libs/libdbusmenu but to compile that package it needs the gtk3 use flag, you run
ptghelper chuse spotify dev-libs/libdbusmenu gtk3

Acp-lic:

ptghelper acp-lic <package or dependency> <license to accept>

Example:

Spotify is proprietary software so to download it you need to accept the license, you run
ptghelper acp-lic  media-sound/spotify Spotify

I hope you enjoy my tool ^.^
