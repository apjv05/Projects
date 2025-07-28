const { SlashCommandBuilder } = require('discord.js');
const { db } = require('../../data/db.js');
const Motif = require('../../utils/commands/CommandVariables.js');
const path = require('path');

console.log(`${path.basename(__filename)} Loaded!`);

module.exports = {
	data: new SlashCommandBuilder()
		.setName('log-contact')
		.setDescription('Log your DMs!')
		.addUserOption(option =>
			option.setName('member')
				.setDescription(`The member you DM'd`)
				.setRequired(true)
	),
	async execute(interaction) {
		const MemberID = interaction.options.getUser('member').id;
		const User = interaction.user.id;

		const { error } =  await db
			.from('member')
			.update({
				LastContactDate: Motif.Today, 
				LastContactPerson: User
			})
			.eq('UserID', MemberID);
  		
		if (error) {
			console.error(`❌ LogContact.js malfunctioned`, error);
			return;
		}
		console.log('✅ LogContact.js functioned');

		interaction.reply(`You DM'd ${interaction.options.getUser('member')}`);
		console.log('LogContact.js executed');
	},
};