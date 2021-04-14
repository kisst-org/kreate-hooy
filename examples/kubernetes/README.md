# Kubernetes example

This example creates manifest file for 2 applications and some network policies.
- The templates are in the `lib` directory.
- The applications `app1` and `app2` each have their own `kreate.sh`
- There is a separate `network` directory with it's own `kreate.sh`, and some unique file

The `kreate.sh` for an application `app1` is as follows:
```
#!/bin/bash
cd "$(dirname "$0")"

export APP=app1
#APP_REPLICAS=1
#APP_CPU_LIMIT=500m
#APP_MEMORY_LIMIT=512Mi

export APP_LABELS="use-db=enabled use-ext-app8=enabled"

../lib/deployment.sh
../lib/service.sh
../lib/ingress.sh
```
This file is a pretty simple bash script that does the following:
- change the directory to the location of the script, because this is where the files will be created.
- export some variables to be used in the templates (some are not used, so the template will use a default value)
- call the template scripts. Each script is an executable file and will create one file.

An example of such a template is the service.sh:
```
#!/bin/bash

FILE=$APP-service.yaml
$KREATE_FILE

cat >$FILE  <<EOF
kind: Service
apiVersion: v1
metadata:
  name: $APP-service
spec:
  selector:
    app: $APP
  ports:
  - protocol: TCP
    port: 8080
    targetPort: 8080
EOF
$KREATE_DONE
```
The main part of this file is the bash-here `cat >$FILE  <<EOF` command. 
This is a basic bash construct that could be seen as a simple template, where variable substitution (`$APP`) will work.
You could use any code you would like, for templating.
It is recommended to stick to bash and simple Linux commands, such as grep, sed or date, but if you ant to use python, perl or whatever, it is possible (but will require it to be installed).

Next to the template code there are a few other things in the template script:
- It does **not** change directory, so the file will be created in the (working) directory from which the script is called (e.g. `app1`)
- It defines a (local) variable `FILE` with the name of the file that will be created. 
  This variable might be used by the `$KREATE_FILE` command, so must precede that line.
  This variable needs not to be exported.
- Before it starts creating a file, there is a `$KREATE_FILE` command
- After it created a file, there is a `$KREATE_DONE` command
The `$KREATE_FILE` and `$KREATE_DONE` commands are not really commands, just environment variables.
If you would run the `service.sh` script from scratch (or run the `app1/kreate.sh` script from scratch), these environment variables will not be defined and thus nothing will happen, which is just fine.
If you run the `kreate` tool, it will set these environment variables to functions to do some usefull things.

Now we can run the `kreate.sh` script for `app1` directly:
```
~/kreate $ cd examples/kubernetes

~/kreate/examples/kubernetes$  git status .
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean

~/kreate/examples/kubernetes$ app1/kreate.sh

~/kreate/examples/kubernetes$ git status .
On branch main
Your branch is up to date with 'origin/main'.

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        app1/app1-deployment.yaml
        app1/app1-ingress.yaml
        app1/app1-service.yaml

nothing added to commit but untracked files present (use "git add" to track)
```

The script does not generate any output, but with git it is easy to see that 3 new files are created.
You can decide if you want to put these files under version control, but that is not necessary since they can easliy be regenerated at anytime.

You can also call the same script using the `kreate` tool.
This will generate a bit more output:
```
~/kreate/examples/kubernetes$ kreate app1
kreating /home/mark/kreate/examples/kubernetes/app1/app1-deployment.yaml
kreating /home/mark/kreate/examples/kubernetes/app1/app1-service.yaml
kreating /home/mark/kreate/examples/kubernetes/app1/app1-ingress.yaml
```

You can also see if any files changed by using the `--status` option (shorthand `-s`).
```
~/kreate/examples/kubernetes$ kreate --status app1
. app1-deployment.yaml
. app1-service.yaml
. app1-ingress.yaml

~/kreate/examples/kubernetes$ rm app1/*yaml; kreate -s app1
+ app1-deployment.yaml
+ app1-service.yaml
+ app1-ingress.yaml
````
- In the first example the files were generated for the second time, so nothing is changed, which is indicated by a period .
- In the second example the files were removed first, so the files would be added, which is indicated by a plus sign +


