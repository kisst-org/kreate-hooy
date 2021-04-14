#!/bin/bash

FILE=egress-$APP.yaml
$KREATE_FILE

cat >$FILE <<EOF
kind: NetworkPolicy
apiVersion: networking.k8s.io/v1
metadata:
  name: egress-$APP
spec:
  podSelector:
    matchLabels:
      use-$APP: enabled
  policyTypes:
    - Egress
  egress:
    - to:
        - ipBlock:
            cidr: "$APP_IP/32"
      ports:
        - port: ${APP_PORT-8080}
          protocol: TCP
EOF
$KREATE_DONE
