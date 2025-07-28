const { SlashCommandBuilder } = require('discord.js');
const { db } = require('../../data/db');
const path = require('path');

console.log(`${path.basename(__filename)} Loaded!`);

module.exports = {
    data: new SlashCommandBuilder()
        .setName('log-comment')
        .setDescription('Make a comment about a user!')
        .addUserOption(option =>
            option.setName('member')
                .setDescription(`The member you are commenting about`)
                .setRequired(true)
        )
        .addStringOption(option =>
            option.setName('comment')
                .setDescription('The comment you want to make')
                .setRequired(true)
        ),
    async execute(interaction) {
        const member = interaction.options.getUser('member');
        const memberid = member.id;
        const comment = interaction.options.getString('comment');
        
        const { error } = await db
            .from('member')
            .update({Comments: comment})
            .eq('UserID', memberid);

        if (error) {
            console.error(`❌ LogComment.js malfunctioned`, error);
            return;
        }
        console.log('✅ LogComment.js functioned');

        interaction.reply(`You commented ${member} as "${comment}"`);
        console.log('LogComment.js executed');
    },
};