const { SlashCommandBuilder } = require('discord.js');
const { db } = require('../../data/db.js');
const path = require('path');

console.log(`${path.basename(__filename)} Loaded!`);

module.exports = {
	data: new SlashCommandBuilder()
		.setName('remove-user')
		.setDescription('remove someone from the db')
		.addUserOption(option =>
			option.setName('member')
				.setDescription(`The member you will remove from the database`)
				.setRequired(true)
	),
	async execute(interaction) {
		const MemberID = interaction.options.getUser('member').id;

		const { error } =  await db
			.from('member')
			.delete()
			.eq('UserID', MemberID);
  		
		if (error) {
			console.error(`RemoveUser.js malfunctioned`, error);
			return;
		}
		console.log('RemoveUser.js functioned');

		interaction.reply(`You removed ${interaction.options.getUser('member')} from the database`);
		console.log('RemoveUser.js executed');
	},
};