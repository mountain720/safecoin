FROM ubuntu:16.04
MAINTAINER <safe@safecoin.org>

RUN printf "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu xenial main \ndeb-src http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu xenial main \n" >> /etc/apt/sources.list && \
    DEBIAN_FRONTEND=noninteractive apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 60C317803A41BA51845E371A1E9377A2BA9EF27F && \
    apt-get -y update && \
    apt-get -y upgrade && \
    apt-get -y install build-essential pkg-config libc6-dev m4 g++-multilib autoconf libtool ncurses-dev \
    unzip python zlib1g-dev wget bsdmainutils automake libssl-dev libprotobuf-dev gcc-8 g++-8 \
    protobuf-compiler libqrencode-dev libdb++-dev software-properties-common libcurl4-openssl-dev curl && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 60 --slave /usr/bin/g++ g++ /usr/bin/g++-8 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

ADD ./ /safecoin
ENV HOME /safecoin
WORKDIR /safecoin

# configure || true or it WILL halt
RUN cd /safecoin && \
    ./autogen.sh && \
    ./configure --with-incompatible-bdb --with-gui || true && \
    ./zcutil/build.sh -j$(nproc)

# Unknown stuff goes here

RUN ln -sf /safecoin/src/safecoind /usr/bin/safecoind && \
    ln -sf /safecoin/zcutil/docker-entrypoint.sh /usr/bin/entrypoint && \
    ln -sf /safecoin/zcutil/docker-safecoin-cli.sh /usr/bin/safecoin-cli

CMD ["entrypoint"]
