#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

SAFECOIND=${SAFECOIND:-$SRCDIR/safecoind}
SAFECOINCLI=${SAFECOINCLI:-$SRCDIR/safecoin-cli}
SAFECOINTX=${SAFECOINTX:-$SRCDIR/safecoin-tx}

[ ! -x $SAFECOIND ] && echo "$SAFECOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
SAFEVER=($($SAFECOINCLI --version | head -n1 | awk -F'[ -]' '{ print $5, $6 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for safecoind if --version-string is not set,
# but has different outcomes for safecoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$SAFECOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $SAFECOIND $SAFECOINCLI $SAFECOINTX; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${SAFEVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${SAFEVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
