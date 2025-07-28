const { Events } = require('discord.js');
const path = require('path');

console.log(`${path.basename(__filename)} Loaded!`);

module.exports = {
    name: Events.MessageCreate,
    once: false,
    async execute(message) {
        //if the message is from a bot, ignore
        if(message.author.bot) return;

        //if the message is not in a guild? ignore 
        if(!message.guild) return;

        const command = message.content.toLowerCase();
        if(command === 'ping' || command === 'ping!') await message.reply('Pong!');
    }
}