#!/bin/bash

#set -ex

echo "...Checking safecoin.conf"

if [ ! -e "$HOME/.safecoin/safecoin.conf" ]; then
    mkdir -p $HOME/.safecoin

    echo "...Creating safecoin.conf"
    cat <<EOF > $HOME/.safecoin/safecoin.conf
rpcuser=${rpcuser:-safecoinrpc}
rpcpassword=${rpcpassword:-`dd if=/dev/urandom bs=33 count=1 2>/dev/null | base64`}
txindex=1
bind=${listenip:-127.0.0.1}
rpcbind=${listenip:-127.0.0.1}
EOF

    cat $HOME/.safecoin/safecoin.conf
fi

echo "...Checking fetch-params"
$HOME/zcutil/fetch-params.sh
echo "Initialization completed successfully"
echo

# ToDo: Needs some rework. I was sick
if [ $# -gt 0 ]; then

    args=("$@")

elif [  -z ${assetchain+x} ]; then

    args=("-gen -genproclimit=${genproclimit:-2} -pubkey=${pubkey}")

else

    args=("-pubkey=${pubkey} -ac_name=${assetchain} -addnode=${seednode}")

fi

echo
echo "****************************************************"
echo "Running: safecoind ${args[@]}"
echo "****************************************************"

exec safecoind ${args[@]}
