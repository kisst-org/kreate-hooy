####################################
# command diff
commands+=(diff)
kreate_start_diff() {
    export KREATE_FILE=kreate_tmp_file
    export KREATE_DONE=kreate_file_diff
}
kreate_final_diff() {
    return
}
kreate_file_diff() {
    if [[ -f $ORIG_FILE ]]; then
        info diff $ORIG_FILE
        diff $ORIG_FILE $FILE
    else
        info no original file $ORIG_FILE
    fi
    rm $FILE
    FILE=$ORIG_FILE
}
export -f kreate_file_diff
kreate_help_diff() {
    echo 'kreate temporary files, do: diff per file'
}
