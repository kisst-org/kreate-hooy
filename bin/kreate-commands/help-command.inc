#####################################################################
# command help
commands+=(help)
kreate_start_help() {
    cat << EOF
Usage: ${0##*/} [options] [command] <dir>...

The purpose of kreate is calling kreate.sh to create files
and then optionally execute a command like git or kustomize
Options can be:
    -h|--help      display this help and exit
    -v|--verbose   verbose mode.
    -q|--quiet     quiet mode.
    --debug        debug info
    --rm           remove kreated files after all is done
    -i|--init-file use another init file
One of the following commands can be specified:
EOF
for cmd in "${commands[@]}" ; do
    printf "%10s   " $cmd
    kreate_help_$cmd
done
cat <<EOF

Commands may be prefixed with --, e.g. --diff, or abbreviated with fewer letters
If no command is given, the default command is 'files'
If no directory is given, the current directory . is used
If the first argument matches a directory with a kreate.sh script, it is not
interpreted as command. To specify a command, one can prefix it with --
EOF
}
kreate_help_help() {
    echo 'display this help and exit (alias -h)'
}
