FROM fedora

RUN dnf groupinstall -y "Development Tools"
RUN dnf groupinstall -y "Development Libraries"
RUN dnf groupinstall -y "C Development Tools and Libraries"
RUN dnf install -y cmake

#==================================================
# Clone tgbot dependent
#==================================================

RUN git clone https://github.com/reo7sp/tgbot-cpp.git /tnp/tgbot

WORKDIR /tnp/tgbot/build

RUN cmake ..
RUN cmake --build . --target install --config release

#==================================================
# BOD
#==================================================

ADD ./app /app/app
ADD ./include /app/include
ADD ./src /app/src
ADD ./third_party /app/third_party
ADD ./CMakeLists.txt /app/CMakeLists.txt

WORKDIR /app/build

RUN cmake ..
RUN cmake --build . --config release

# Добавим пользователя, потому как в Docker по умолчанию используется root
# Запускать незнакомое приложение под root'ом неприлично :)
RUN groupadd -r sample && useradd -r -g sample sample
USER sample

# Установим точку входа
ENTRYPOINT ["/app/build/app/bot_of_duty_app"]