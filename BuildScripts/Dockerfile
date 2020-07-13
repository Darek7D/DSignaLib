FROM qt
RUN apt update

RUN mkdir /output
WORKDIR /build

COPY . /dsignal

RUN i686-w64-mingw32.shared.posix-cmake -DUSE_FENV_ACCESS=OFF -DCMAKE_INSTALL_PREFIX=/output/ /dsignal && make && make install