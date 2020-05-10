#!/usr/local/bin/bash

# Display all the mounted file systems who are either smaller than than 1GB or have less than 20% free space.

files=$(cat utils/df.fake | awk 'if ($2 < 1024)')

echo $files


