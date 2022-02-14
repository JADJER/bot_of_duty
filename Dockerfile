FROM fedora

RUN dnf groupinstall -y "Development Tools"
RUN dnf install -y cmake perl python-pip

RUN useradd -ms /bin/bash bot
USER bot

ENV PATH="/home/bot/.local/bin:$PATH"

RUN pip install conan

RUN mkdir -p /home/bot/app/src
RUN chown -R bot /home/bot/app

WORKDIR /home/bot/app

COPY . ./src

RUN conan install src --build=missing -s compiler.libcxx=libstdc++11

RUN cmake src
RUN cmake --build . --config release

# Установим точку входа
ENTRYPOINT ["/home/bot/app/bin/bot_of_duty_app"]