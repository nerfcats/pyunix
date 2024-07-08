#!/bin/bash

# GitHub repository URL and file path
GITHUB_REPO="https://raw.githubusercontent.com/noahdossan/pyunix/master"
GITHUB_VER_FILE="ver.txt"

# Local file path
LOCAL_VER_FILE="ver.txt"

# Function to compare version strings
version_gt() { test "$(printf '%s\n' "$@" | sort -V | head -n 1)" != "$1"; }

echo "PYunix update and compiler utility"

# Fetch latest version from GitHub
echo "Fetching latest version from GitHub..."
wget -q "$GITHUB_REPO/$GITHUB_VER_FILE" -O /tmp/latest_ver.txt
GITHUB_VERSION=$(cat /tmp/latest_ver.txt)

# Check if ver.txt exists locally
if [ ! -f "$LOCAL_VER_FILE" ]; then
    echo "Local version file '$LOCAL_VER_FILE' not found. Aborting."
    exit 1
fi

# Read local version
LOCAL_VERSION=$(cat "$LOCAL_VER_FILE")

# Compare versions
if version_gt "$GITHUB_VERSION" "$LOCAL_VERSION"; then
    echo "A new version ($GITHUB_VERSION) is available. Current version is $LOCAL_VERSION."
    echo "Do you want to update? Be careful, ALL changes to code and configs will be erased! The old version will be stored in a backup folder. (yes/no)"
    read -r response
    if [[ $response =~ ^([yY][eE][sS]|[yY])$ ]]; then
        # Backup current directory
        BACKUP_DIR="backup_$(date +'%Y%m%d_%H%M%S')"
        mkdir "$BACKUP_DIR"
        cp -r ./* "$BACKUP_DIR/"

        # Clean up backup of ver.txt since it will be replaced
        rm -f "$BACKUP_DIR/ver.txt"

        # Update with new version
        wget -q "$GITHUB_REPO/$GITHUB_VER_FILE" -O "$LOCAL_VER_FILE"
        echo "Update complete. Version $GITHUB_VERSION is now installed."
    else
        echo "Update declined. Exiting."
    fi
elif [ "$GITHUB_VERSION" = "$LOCAL_VERSION" ]; then
    echo "You are already using the latest version ($LOCAL_VERSION)."
else
    echo "Local version ($LOCAL_VERSION) is newer or same as GitHub version ($GITHUB_VERSION). No update needed."
fi

# Clean up temporary file
rm -f /tmp/latest_ver.txt

echo "Finished setup. Compiling and running in 2s"
sleep 2s
# Compile source
gcc -o main src/main.c -rdynamic -lbacktrace

# Run source
./main
