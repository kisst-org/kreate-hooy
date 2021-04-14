labels() {
    for label in ${APP_LABELS}; do
        printf "\n        $(echo $label| sed -e 's/=/: /')"
    done
}
