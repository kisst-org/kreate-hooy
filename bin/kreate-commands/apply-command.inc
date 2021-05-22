####################################
# apply
####################################
commands+=(apply)
command_alias[-a]=apply
kreate_start_apply() {
    export KREATE_FILE=kreate_file
    unset KREATE_DONE
    export KREATE_APPLY=kreate_final_apply
}

kreate_final_apply() {
    if [[ -z $KUBECTL_CONTEXT ]]; then
        echo KUBECTL_CONTEXT is not set
        exit 1
    fi
    info kustomize build $KREATE_TARGET_DIR \| kubectl apply --context $KUBECTL_CONTEXT -f -
    kustomize build $KREATE_TARGET_DIR | kubectl apply --context $KUBECTL_CONTEXT -f -
}
export -f kreate_final_apply

kreate_help_apply() {
    echo 'kreate files, do: kustomize build | kubectl apply -f -  (alias -a)'
}
