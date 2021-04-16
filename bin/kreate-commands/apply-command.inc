####################################
# apply
####################################
commands+=(apply)
command_alias[-a]=apply
kreate_start_apply() {
    export KREATE_FILE=kreate_file
    unset KREATE_DONE
}

kreate_final_apply() {
    info kustomize build $1 \| kubectl apply -f -
    kustomize build $1 | kubectl apply -f -
}

kreate_help_apply() {
    echo 'apply    kreate files, do: kustomize build | kubectl apply -f -'
}
