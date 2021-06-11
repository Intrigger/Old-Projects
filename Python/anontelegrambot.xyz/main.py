# coding=UTF-8
import numpy
import requests
import pprint
import time
import json
import random
import datetime
import time
import math
import sqlite3
import matplotlib.pyplot as plt

#################################################################



request_const = "https://api.telegram.org/bot1766694174:AAEWmctUlPQ1gMml-d9ZCPxbaT3NcbSPVU4/"


#################################################################

conn = sqlite3.connect('users_data.db')
cur = conn.cursor()
cur.execute(
    """
    CREATE TABLE IF NOT EXISTS users(
    id INT PRIMARY KEY,
    tokens INT,
    sex TEXT);
    """
)
conn.commit()

DELETED_USERS = 0

cur.execute("SELECT * FROM users")
conn.commit()

users_data = cur.fetchall()



r = requests.get(request_const + "getUpdates").json()

offset = 0
if 'result' in r:
    if len(r['result']) > 0:
        offset = r['result'][-1]['update_id'] + 1
        r = requests.get(request_const + "getUpdates?offset={}".format(offset)).json()

boss_id = 1412967731

choose_sex_kb = {
    'inline_keyboard': [
        [
            {
                'text': "Мужской 👨",
                'callback_data': 'Reg Man'
            },
            {
                'text': "Женский 👩",
                'callback_data': 'Reg Woman'
            }
        ]
    ]
}
find_kb = {
    'inline_keyboard': [
        [
            {
                'text': "Парня 👨",
                'callback_data': 'Find Man'
            },
            {
                'text': "Девушку 👩",
                'callback_data': 'Find Woman'
            }
        ]
    ]
}

find_markup = json.dumps(find_kb)

choose_sex_string = json.dumps(choose_sex_kb)

users_list = []
users_ids = []
for data in users_data:
    users_list.append(dict(id=data[0], tokens=data[1], sex=data[2]))
    users_ids.append(data[0])

users_data = users_list
print("USERS_DATA: \n")
for userd in users_data:
    print(userd)

queue = []
chats = []

searching_man_queue = []
searching_woman_queue = []

stop_bot = False

MESSAGES_COUNT = 0
NEW_USER_COUNT = 0

MESSAGES_STATS = []

lastTimeHour = math.floor(time.time())
lastTimeDay = math.floor(time.time())

day = datetime.datetime.now().day

while not stop_bot:

    if datetime.datetime.now().hour == 0:
        if datetime.datetime.now().day != day:
            day = datetime.datetime.now().day
            for userd in range(0, len(users_data)):
                users_data[userd]['tokens'] += 5
                cur.execute("""
                        INSERT OR IGNORE INTO users(id, tokens, sex) VALUES ('{}', '{}', '{}')
                        """.format(users_data[userd]['id'], users_data[userd]['tokens'], users_data[userd]['sex']))
                conn.commit()

    # ищем девушек
    for finder in searching_woman_queue:
        finder_sex = "none"
        for userd in users_data:
            if userd['id'] == finder:
                finder_sex = userd['sex']
                break

        for user in queue:
            if user == finder:
                continue
            user_sex = "none"
            for userd in users_data:
                if userd['id'] == user:
                    user_sex = userd['sex']
                    break
            if (user_sex == "Woman"):
                if ((finder_sex == "Man") and (user not in searching_woman_queue)) or (
                        (finder_sex == "Woman") and (user not in searching_man_queue)):

                    for userd in range(0, len(users_data)):
                        if users_data[userd]['id'] == finder:
                            users_data[userd]['tokens'] -= 1
                            break
                    if (user in searching_woman_queue) or (user in searching_man_queue):
                        for userd in range(0, len(users_data)):
                            if users_data[userd]['id'] == user:
                                users_data[userd]['tokens'] -= 1
                                break

                    _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                     "&text={}".format(
                        finder, "Ваша собеседница найдена!"
                    ))
                    _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                     "&text={}".format(
                        user, "Ваш собеседник найден!"
                    ))
                    chats.append([finder, user])
                    try:
                        searching_woman_queue.remove(finder)
                        queue.remove(user)
                        queue.remove(finder)
                    except:
                        pass
                    break

    # ищем парней
    for finder in searching_man_queue:
        finder_sex = "none"
        for userd in users_data:
            if userd['id'] == finder:
                finder_sex = userd['sex']
                break

        for user in queue:
            if user == finder:
                continue
            user_sex = "none"
            for userd in users_data:
                if userd['id'] == user:
                    user_sex = userd['sex']
                    break
            if (user_sex == "Man"):
                if ((finder_sex == "Man") and (user not in searching_woman_queue)) or (
                        (finder_sex == "Woman") and (user not in searching_man_queue)):
                    for userd in range(0, len(users_data)):
                        if users_data[userd]['id'] == finder:
                            users_data[userd]['tokens'] -= 1
                            break
                    if (user in searching_woman_queue) or (user in searching_man_queue):
                        for userd in range(0, len(users_data)):
                            if users_data[userd]['id'] == user:
                                users_data[userd]['tokens'] -= 1
                                break
                    _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                     "&text={}".format(
                        finder, "Ваша собеседник найден!"
                    ))
                    _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                     "&text={}".format(
                        user, "Ваш собеседник найден!"
                    ))
                    chats.append([finder, user])
                    searching_man_queue.remove(finder)
                    try:
                        queue.remove(user)
                        queue.remove(finder)
                    except:
                        pass
                    break
    queue_len = 0
    new_queue = []
    for i in queue:
        if (i not in searching_woman_queue) and (i not in searching_man_queue):
            new_queue.append(i)
    while len(new_queue) > 1:
        first = random.choice(new_queue)
        second = random.choice(new_queue)
        while first == second:
            first = random.choice(new_queue)
            second = random.choice(new_queue)
        _ = requests.get(request_const + "sendMessage?chat_id={}"
                                         "&text={}".format(
            first, "Ваш собеседник найден!\n"
                   "Следующий чат - /next\n"
            # "Найти по полу - /find\n"
                   "Остановить чат - /stop\n"
                   "\nПриятного общения! 😁"

        ))
        _ = requests.get(request_const + "sendMessage?chat_id={}"
                                         "&text={}".format(
            second, "Ваш собеседник найден!\n"
                    "Следующий чат - /next\n"
            # "Найти по полу - /find\n"
                    "Остановить чат - /stop\n"
                    "\nПриятного общения! 😁"
        ))
        chats.append([first, second])

        queue.remove(first)
        queue.remove(second)
        new_queue.remove(first)
        new_queue.remove(second)

    if math.floor(time.time()) - math.floor(lastTimeHour) >= 60:
        lastTimeHour = math.floor(time.time())
        MESSAGES_STATS.append(MESSAGES_COUNT)
        MESSAGES_COUNT = 0

    if len(MESSAGES_STATS) == (60 * 24):
        lastTimeDay = math.floor(time.time())
        _ = requests.get(request_const + "sendMessage?chat_id={}"
                                         "&text={}".format(
            1412967731, "STATS: {} newUsers/lastDay\n{} deleted users".format(NEW_USER_COUNT, DELETED_USERS)
        ))
        x = numpy.linspace(0, 60*24-1, 60*24)
        plt.plot(x, MESSAGES_STATS)
        print(datetime.date.today())
        filename = "stats/fig-{}.png".format(datetime.date.today())
        plt.savefig(filename)

        files = {'photo': open(filename, 'rb')}

        _ = requests.post(request_const + "sendPhoto?chat_id={}"
                                                    "photo=@{}".format(
            1412967731, open(filename)
        ), files=files)
        NEW_USER_COUNT = 0
        DELETED_USERS = 0
        MESSAGES_STATS.clear()

    if offset == 0:
        r = requests.get(request_const + "getUpdates").json()
        if 'result' in r:
            if len(r['result']) > 0:
                offset = r['result'][0]['update_id']
    else:
        r = requests.get(request_const + "getUpdates?offset={}".format(offset)).json()
    if 'result' in r:
        for result in r['result']:
            if 'callback_query' in result:
                callback_query = result['callback_query']
                if str(callback_query['data']).split(' ')[0] == 'Reg':
                    user = dict(id=callback_query['from']['id'], tokens=20,
                                sex=str(callback_query['data']).split(' ')[1])
                    req = requests.get(request_const + "sendMessage?"
                                                       "chat_id={}"
                                                       "&text={}&parse_mode=HTML".format(
                        callback_query['from']['id'],
                        "<i>🔎\tНайти собеседника: /next\n\n"
                        "🛑"
                        "\tОстановить чат: /stop\n\n"
                        # "⚤\t\tПоиск по полу: /find\n\n"
                        "</i>"
                    ))
                    if user['id'] not in users_ids:
                        print("\033[32m{} NEW USER {}\033[0m".format(datetime.datetime.now(),
                                                                     callback_query['from']['id']))
                        NEW_USER_COUNT += 1
                        cur.execute("""
                        INSERT OR IGNORE INTO users(id, tokens, sex) VALUES ('{}', '{}', '{}')
                        """.format(user['id'], user['tokens'], user['sex']))
                        conn.commit()
                        users_ids.append(callback_query['from']['id'])
                        users_data.append(user)
                elif str(callback_query['data']).split(' ')[0] == 'Find':
                    inChat = False
                    companion = 0
                    for chat in chats:
                        if (chat[0] == callback_query['from']['id']):
                            inChat = True
                            companion = chat[1]
                            break
                        if (chat[1] == callback_query['from']['id']):
                            companion = chat[0]
                            inChat = True
                            break
                    if inChat:
                        _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                         "&text={}".format(
                            callback_query['from']['id'], "Вы уже в чате!", find_markup
                        ))
                    else:
                        _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                         "&text={}".format(
                            callback_query['from']['id'], "Начинаем поиск вашего собеседника!", find_markup
                        ))

                        if callback_query['from']['id'] not in queue:
                            queue.append(callback_query['from']['id'])
                        if str(callback_query['data']).split(' ')[1] == "Man":
                            searching_man_queue.append(callback_query['from']['id'])
                        elif str(callback_query['data']).split(' ')[1] == "Woman":
                            searching_woman_queue.append(callback_query['from']['id'])

            if 'message' in result:
                MESSAGES_COUNT += 1
                message = result['message']
                req = requests.get(request_const + "getChatMember?chat_id={}&user_id={}".format(
                    "@AnonChatBotTelegram",
                    message['from']['id']
                )).json()
                cur.execute("SELECT * FROM users WHERE id={}".format(message['from']['id']))
                conn.commit()
                temp_data = cur.fetchall()
                if (req['result']['status'] == 'left') and (len(temp_data) != 0):
                    _ = requests.get(request_const + "sendMessage?chat_id={}&text={}&parse_mode=HTML".format(
                        message['from']['id'],
                        '<b>Чтобы начать пользоваться ботом подпишитесь на наш канал:\n'
                        '@AnonChatBotTelegram\nи нажмите /start !</b>'
                    ))
                    continue
                if 'text' in message:

                    if str(message['text']).split(' ')[0] == '/start':

                        if len(str(message['text']).split(' ')) == 1:
                            req = requests.get(request_const + "sendMessage?chat_id={}"
                            # pprint.pprint(message)
                                                               "&text={}"
                                                               "&reply_markup={}&parse_mode=HTML".format(
                                message['from']['id'],

                                "<b>"
                                "Добро пожаловать в Анонимный чат!\n"
                                "В этом уютном месте ты можешь общаться "
                                "со случайными людьми!)\n"
                                "\nИнстуркция по использованию:\n"
                                "/next - Начать поиск собеседника\n"
                                "/stop - Остановить поиск / общение\n"
                                # "/find - Найти собеседника по полу\n"
                                "/invite - Пригласить друга и получить 10💎\n"
                                "/buy - Купить токенов\n"
                                "Приятного общения!)\n\n"
                                "\nВнимание, в боте действует система токенов 💎:\n"
                                "За них можно искать собеседника по полу.\n"
                                # "Для этого просто введите /find !\n\n"
                                "<u><i>Выберите свой пол: </i></u>"
                                "</b>"
                                ,
                                choose_sex_string
                            ))
                        elif len(str(message['text']).split(' ')) == 2:
                            inviter = int(str(message['text']).split(' ')[1])
                            invited = message['from']['id']
                            cur.execute(
                                "SELECT * FROM users WHERE id={}".format(invited)
                            )
                            conn.commit()
                            temp_data = cur.fetchall()
                            inviter_tokens = 0
                            for userd in users_data:
                                if userd['id'] == inviter:
                                    inviter_tokens = userd['tokens']
                                    break

                            if len(temp_data) == 0:
                                cur.execute(
                                    "UPDATE users SET tokens={} WHERE id={}".format(inviter_tokens + 10, inviter)
                                )
                                conn.commit()
                            else:
                                _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                                 "&text={}".format(
                                    message['from']['id'], "Вы уже зарегистированы!"
                                ))
                            req = requests.get(request_const + "sendMessage?chat_id={}"
                                                               "&text={}"
                                                               "&reply_markup={}&parse_mode=HTML".format(
                                message['from']['id'],

                                "<b>"
                                "Добро пожаловать в Анонимный чат!\n"
                                "В этом уютном месте ты можешь общаться "
                                "со случайными людьми!)\n"
                                "\nИнстуркция по использованию:\n"
                                "/next - Начать поиск собеседника\n"
                                "/stop - Остановить поиск / общение\n"
                                # "/find - Найти собеседника по полу\n"
                                "/buy - Купить токенов\n"
                                "Приятного общения!)\n\n"
                                "<u><i>Выберите свой пол: </i></u>"
                                "</b>"
                                ,
                                choose_sex_string
                            ))
                    elif message['text'] == '/next':
                        if message['from']['id'] not in users_ids:
                            _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                             "&text={}".format(
                                message['from']['id'], "Сначала нажмите /start !",
                            ))
                            continue
                        inChat = False
                        companion = 0
                        for chat in chats:
                            if (chat[0] == message['from']['id']):
                                inChat = True
                                companion = chat[1]
                                break
                            if (chat[1] == message['from']['id']):
                                companion = chat[0]
                                inChat = True
                                break

                        if inChat:
                            _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                             "&text={}".format(
                                message['from']['id'], "Вы окончили чат!"
                            ))
                            _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                             "&text={}".format(
                                companion,
                                "Ваш собеседник покинул чат!"
                                ""
                            ))
                            if [message['from']['id'], companion] in chats:
                                chats.remove([message['from']['id'], companion])
                            if [companion, message['from']['id']] in chats:
                                chats.remove([companion, message['from']['id']])

                        if message['from']['id'] not in queue:
                            queue.append(message['from']['id'])
                            req = requests.get(request_const + "sendMessage?chat_id={}"
                                                               "&text={}".format(
                                message['from']['id'], "Начинаем поиск собеседника!"
                            ))
                        else:
                            req = requests.get(request_const + "sendMessage?chat_id={}"
                                                               "&text={}".format(
                                message['from']['id'], "Вы уже в поиске!"
                            ))
                    elif message['text'] == '/stop':

                        if (message['from']['id'] in queue) or (message['from']['id'] in searching_man_queue) or (
                                message['from']['id'] in searching_woman_queue):

                            if (message['from']['id'] in queue):
                                queue.remove(message['from']['id'])
                            if (message['from']['id'] in searching_man_queue):
                                searching_man_queue.remove(message['from']['id'])
                            if (message['from']['id'] in searching_woman_queue):
                                searching_woman_queue.remove(message['from']['id'])
                            _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                             "&text={}".format(
                                message['from']['id'], "Вы остановили поиск!"
                            ))
                        else:
                            inChat = False
                            companion = 0
                            for chat in chats:
                                if (chat[0] == message['from']['id']):
                                    inChat = True
                                    companion = chat[1]
                                    break
                                if (chat[1] == message['from']['id']):
                                    companion = chat[0]
                                    inChat = True
                                    break
                            if inChat:
                                for chat in chats:
                                    if chat[0] == message['from']['id']:
                                        _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                                         "&text={}".format(
                                            message['from']['id'], "Вы закончили диалог!",
                                        ))
                                        _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                                         "&text={}".format(
                                            chat[1], "Ваш собеседник покинул чат!",
                                        ))
                                        chats.remove(chat)
                                        break
                                    if chat[1] == message['from']['id']:
                                        _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                                         "&text={}".format(
                                            chat[1], "Вы закончили диалог!",
                                        ))
                                        _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                                         "&text={}".format(
                                            message['from']['id'], "Ваш собеседник покинул чат!",
                                        ))
                                        chats.remove(chat)
                                        break
                            else:
                                _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                                 "&text={}".format(
                                    message['from']['id'], "Вы не в чате!",
                                ))
                    elif message['text'] == '/invite':
                        _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                         "&text={}".format(
                            message['from']['id'],
                            "Чтобы пригласить друзей и получить по 10 💎 за каждого из них, отправь им это сообщение: \n"
                        ))
                        _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                         "&text={}".format(
                            message['from']['id'],
                            "https://t.me/anonTelegramBot?start={}".format(message['from']['id'])
                        ))
                    elif message['text'] == '/tokens':
                        tokens = 0
                        for userd in users_data:
                            if userd['id'] == message['from']['id']:
                                tokens = userd['tokens']
                                break
                        _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                         "&text={}".format(
                            message['from']['id'], "У вас {} токенов 💎\n"
                                                   "Ты получаешь по 5 💎 каждый день бесплатно!".format(tokens)
                        ))
                    elif message['text'] == '/restart_bot':
                        for userd in range(0, len(users_data)):
                            cur.execute(
                                "UPDATE users SET tokens= {} WHERE id={}"
                                    .format(users_data[userd]['tokens'], users_data[userd]['id']))
                            conn.commit()
                        cur.execute("SELECT * FROM users")
                        conn.commit()
                        data_list = (cur.fetchall())
                        for data in data_list:
                            print(data)
                        for user_id in users_ids:

                            try:
                                query = requests.get(request_const + "sendMessage?chat_id={}"
                                                                     "&text={}".format(
                                    user_id, "Уведомление от админа бота:\n"
                                             "Уважаемые пользователи бота, "
                                             "cейчас бот будет перезагружен.\n"
                                             "Для перезагрузки нажмите /start\n"
                                             "Спасибо за понимание!"
                                )).json()
                            except Exception as e:
                                print(e)
                        _ = requests.get(request_const + "getUpdates?offset={}".format(message['message_id'])).json()
                        stop_bot = True
                    elif message['text'] == '/buy':
                        if message['from']['id'] not in users_ids:
                            _ = requests.get(request_const + "sendMessage?chat_id={}"
                                                             "&text={}".format(
                                message['from']['id'], "Сперва нажмите /start !",
                            ))
                        res = requests.get(request_const + "sendMessage?chat_id={}"
                                                           "&text={}&parse_mode=HTML".format(
                            message['from']['id'],
                            "Итак, вы решили приобрести токены!\n"
                            "Отлично, тогда <u><b>ВНИМАТЕЛЬНО</b></u> прочитай это сообщение!\n"
                            "Когда ты нажмешь на <b><u><i>ссылку ниже</i></u></b>, ты перейдешь на популярный сайт "
                            "для оплаты онлайн-покупок - <u>YooMoney</u>.\n"
                            "В поле сумма укажи количество <b><u>Токенов</u></b>, которое ты хочешь купить\n"
                            "1 токен = 1 рубль.\n"
                            "Далее, <b><u>ОБЯЗАТЕЛЬНО</u></b> нажми галочку \"Добавить сообщению получателю\""
                            "и вставь туда это число: <b><i>{}</i></b> , иначе Мы не сможем зачислить тебе токены."
                            "\n\n"
                            "Теперь, если ты прочитал инструкцию выше, ты можешь переходить по ссылке:  {}"
                            "\n\nТокены будут начислены в ближайшее время, мы сделаем это максимально быстро!"
                            "\nУдачного пользования ботом!\n"
                                .format(message['from']['id'], "https://yoomoney.ru/to/4100116377314678")
                            ,
                        ))
                    else:
                        try:
                            inChat = False
                            companion = 0
                            for chat in chats:
                                if (chat[0] == message['from']['id']):
                                    inChat = True
                                    companion = chat[1]
                                    break
                                if (chat[1] == message['from']['id']):
                                    companion = chat[0]
                                    inChat = True
                                    break
                            if inChat:
                                req = requests.get(request_const + "copyMessage?"
                                                                   "chat_id={}"
                                                                   "&from_chat_id={}"
                                                                   "&message_id={}".format(
                                    companion,
                                    message['from']['id'],
                                    message['message_id']
                                )).json()
                                if req['ok'] == False:
                                    _ = requests.get(request_const + "sendMessage?chat_id={}&text={}".format(
                                        message['from']['id'],
                                        "Ваш собеседник покинул чат!"
                                    ))
                                    cur.execute(
                                        "DELETE * FROM users WHERE id={}".format(companion)
                                    )
                                    conn.commit()
                                    DELETED_USERS += 1

                        except:
                            pass
                else:
                    try:
                        inChat = False
                        companion = 0
                        for chat in chats:
                            if (chat[0] == message['from']['id']):
                                inChat = True
                                companion = chat[1]
                                break
                            if (chat[1] == message['from']['id']):
                                companion = chat[0]
                                inChat = True
                                break
                        if inChat:
                            req = requests.get(request_const + "copyMessage?"
                                                               "chat_id={}"
                                                               "&from_chat_id={}"
                                                               "&message_id={}".format(
                                companion,
                                message['from']['id'],
                                message['message_id']
                            )).json()
                            if req['ok'] == False:
                                _ = requests.get(request_const + "sendMessage?chat_id={}&text={}".format(
                                    message['from']['id'],
                                    "Ваш собеседник покинул чат!"
                                ))



                    except:
                        pass

        offset += len(r['result'])

    # time.sleep(0.05)

