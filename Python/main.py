import random

import requests
import json
import time

sleep_time = 0.05
url = "https://api.telegram.org/bot"
token = "1637101762:AAFi0uAL6m6CGDPWUStkE_amRgAAiVZFxyA"

json_string = {
    "keyboard":[
        [
            {
            "text": "Мужской"
            },
            {
            "text": "Женский"
            }
        ]
    ],
    "one_time_keyboard": True
}

json_query = json.dumps(json_string)

print(json_query)

result = requests.get(url + token + "/getUpdates").json()

lastUpdateId = 0

log = open("lastUpdateId.log", "r")
lastUpdateId = int(log.read())
log.close()

file = open("usersIds.txt", "r")
usersIds = file.readlines()

for i in range(0, len(usersIds)):
    usersIds[i] = usersIds[i][:-1]

print("LOG: USERS IDS LIST:", usersIds)
file.close()

bossFinishCommand = False

queue = []

chats = []

commandsList = ['/chat', '/next', '/start', '/boss-clear', '/boss-finish']

while not bossFinishCommand:

    if len(queue) > 1:
        iterator = 0
        while len(queue) > 1:
            pair = [queue[0]]
            queue.remove(queue[0])
            pair.append(random.choice(queue))
            chats.append(pair)
            requests.get(url + token + "/sendMessage?chat_id=" + str(pair[0]) + "&text=Ваш собеседник найден!")
            requests.get(url + token + "/sendMessage?chat_id=" + str(pair[1]) + "&text=Ваш собеседник найден!")




    result = requests.get(url + token + "/getUpdates?offset=" + str(lastUpdateId)).json()
    for i in result['result']:
        dictionary = dict(i)
        if lastUpdateId < dictionary['update_id']:
            if 'text' in dictionary['message']:
                if dictionary['message']['text'] == '/start':
                    if str(dictionary['message']['from']['id']) not in usersIds:
                        print("LOG: NEW USER: {}".format(str(dictionary['message']['from']['id'])))
                        usersIds.append(str(dictionary['message']['from']['id']))
                        requests.get(url + token + "/sendMessage?chat_id=" + str(dictionary['message']['chat']['id']) + "&text=Добро пожаловать в бота!")
                        requests.get(url + token + "/sendMessage?chat_id=" + str(dictionary['message']['chat']['id']) + "&text=Чтобы начать поиск собеседника, жми /chat.\n"
                                                                                                                        "Чтобы найти следующего собеседника, жми /next.")
                        requests.get(url + token + "/sendMessage?chat_id=" + str(dictionary['message']['chat']['id']) + "&text=Укажите свой пол: " + "&reply_markup=" + json_query)
                if dictionary['message']['text'] not in commandsList:
                    companion = 0
                    for chat in chats:
                        if (chat[0] == dictionary['message']['from']['id']):
                            companion = chat[1]
                        if (chat[1] == dictionary['message']['from']['id']):
                            companion = chat[0]
                    if companion != 0:
                        requests.get(url + token + "/sendMessage?chat_id=" + str(companion) + "&text=" + dictionary['message']['text'])

                if dictionary['message']['text'] == '/chat':
                    requests.get(url + token + "/sendMessage?chat_id=" + str(
                        dictionary['message']['chat']['id']) + "&text=Начинаем поиск собеседника!")
                    if (dictionary['message']['chat']['id'] not in queue):
                        queue.append(dictionary['message']['chat']['id'])
                    else:
                        requests.get(url + token + "/sendMessage?chat_id=" + str(
                            dictionary['message']['chat']['id']) + "&text=Мы уже ищем вашего собеседника!")

                if dictionary['message']['text'] == '/boss-finish':
                    bossFinishCommand = True
                if dictionary['message']['text'] == '/boss-clear':
                    usersIds.clear()
            else:
                companion = 0
                for chat in chats:
                    if (chat[0] == dictionary['message']['from']['id']):
                        companion = chat[1]
                    if (chat[1] == dictionary['message']['from']['id']):
                        companion = chat[0]
                if companion != 0:
                    requests.get(url+token+"/copyMessage?chat_id=" + str(companion) + "&from_chat_id=" + str(dictionary['message']['chat']['id'])
                                  + "&message_id="  + str(dictionary['message']['message_id']))
            lastUpdateId = dictionary['update_id']
    time.sleep(sleep_time)

print("LOG: BOT STOPPED!")

file = open("lastUpdateId.log", "w")
file.write(str(lastUpdateId))
file.close()
file = open("usersIds.txt", 'w')

for i in usersIds:
    file.write(str(i) + '\r\n')
file.close()

