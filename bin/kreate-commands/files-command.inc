

####################################
# command files
command_alias[-f]=files
commands+=(files)
kreate_start_files() {
    export KREATE_FILE=kreate_file
    unset KREATE_DONE
}
kreate_final_files() {
    return
}
kreate_help_files() {
    echo 'kreate files'
}
