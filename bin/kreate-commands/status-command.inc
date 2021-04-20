####################################
# command status
commands+=(status)
kreate_start_status() {
    export KREATE_FILE=kreate_tmp_file
    export KREATE_DONE=kreate_file_status
}
kreate_final_status() {
    return
}
kreate_file_status() {
    if [[ -f $ORIG_FILE ]]; then
        verbose status $(pwd)/$ORIG_FILE
        if diff -q $ORIG_FILE $FILE >/dev/null; then
            info . $ORIG_FILE
        else
            info M $ORIG_FILE
        fi
    else
        info + $ORIG_FILE
    fi
    rm $FILE
    FILE=$ORIG_FILE
}
export -f kreate_file_status
kreate_help_status() {
    echo 'kreate temporary files, show if files are +/new or M/modified (alias -s)'
}
