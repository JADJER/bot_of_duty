FROM fedora

RUN dnf groupinstall -y "Development Tools"
RUN dnf install -y cmake perl python-pip

RUN useradd -m bot
USER bot

RUN pwd

RUN pip install conan

ADD . /app

WORKDIR /app/build

RUN conan install .. --build=missing

RUN cmake .. -DCMAKE_BUILD_TYPE=Release
RUN cmake --build . --config release



# Установим точку входа
ENTRYPOINT ["/app/build/app/bot_of_duty_app"]