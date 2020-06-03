FROM debian:stretch

RUN apt-get update
RUN apt-get install -y --no-install-recommends \
	autoconf \
	automake \
	autopoint \
	binutils \
	bison \
	build-essential \
	ca-certificates \
	cmake \
	debhelper \
	devscripts \
	fakeroot \
	flex \
	gcc \
	g++ \
	g++-multilib \
	git \
	gperf \
	intltool \
	libc6-dev-i386 \
	libgdk-pixbuf2.0-dev \
	libltdl-dev \
	libssl-dev \
	libffi-dev \
	libgmp-dev \
	libmpc-dev \
	libmpfr-dev \
	libtool \
	libtool-bin \
	libz-dev \
	lzip \
	openssl \
	patch \
	pkg-config \
	p7zip-full \
	ruby \
	scons \
	texinfo \
	unzip \
	wget

RUN apt update

RUN apt install -y xvfb libfontconfig dbus libssl-dev libcurl4-gnutls-dev libxkbcommon-x11-0 libxrender-dev

COPY . /dsignal

RUN mkdir /build /output
WORKDIR /build

RUN i686-w64-mingw32.shared.posix-cmake -DUSE_FENV_ACCESS=OFF -DCMAKE_INSTALL_PREFIX=/output/ /dsignal/DSignal && make && make install