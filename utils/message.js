const TelegramBot = require("node-telegram-bot-api");


function sendText(details) {
    const token = "5099022913:AAFFvQUhwj5KabVl_Uwxhfsh9i-29u4u6xw";
    const bot = new TelegramBot(token);

    bot.sendMessage(details.chatid, `Alcohol was detected by the device with the ID: ${details.id}. Please take appropriate action.`);
}

module.exports = sendText;