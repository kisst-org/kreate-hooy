####################################
# build
####################################
commands+=(build)
command_alias[-b]=build
kreate_start_build() {
    export KREATE_FILE=kreate_file
    unset KREATE_DONE
}

kreate_final_build() {
    info kustomize build $1
    kustomize build $1
}

kreate_help_build() {
    echo 'kreate files, do: kustomize build (alias -b)'
}
