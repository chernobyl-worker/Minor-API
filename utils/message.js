const TelegramBot = require("node-telegram-bot-api");


function sendText(details) {
    const token = env.API_KEY;
    const bot = new TelegramBot(token);

    bot.sendMessage(details.chatid, `Alcohol was detected by the device with the ID: ${details.id}. Please take appropriate action.`);
}

module.exports = sendText;