const { Events } = require('discord.js');
const path = require('path');
const {testConnection} = require('../data/db');

console.log(`${path.basename(__filename)} Loaded!`);

module.exports = {
	name: Events.ClientReady,
	once: true,
	//lets the dev know the bot is logged in
	async execute(client) {
		console.log(`Ready! Logged in as ${client.user.tag}`);
		console.log('Testing supabase connection . . . ');
		await testConnection();
		console.log(`${client.user.tag} is ready`);
	},
};
