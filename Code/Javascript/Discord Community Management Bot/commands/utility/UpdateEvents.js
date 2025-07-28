const { SlashCommandBuilder } = require('discord.js');
const { db } = require('../../data/db');
const path = require('path');

console.log(`${path.basename(__filename)} Loaded!`);

module.exports = {
    data: new SlashCommandBuilder()
        .setName('update-events-attended')
        .setDescription('change a the amount of events a member has atteneded')
        .addUserOption(option =>
            option.setName('member')
                .setDescription(`The member you are changing`)
                .setRequired(true)
        )
        .addIntegerOption(option =>
            option.setName('events-attended')
                .setDescription('amount of events you want to set')
                .setRequired(true)
        ),
    async execute(interaction) {
        const member = interaction.options.getUser('member');
        const memberid = member.id;
        const Num = interaction.options.getInteger('events-attended');
        
        const { error } = await db
            .from('member')
            .update({'EventsAttended': Num})
            .eq('UserID', memberid);

        if (error) {
            console.error(`❌ UpdateRank.js malfunctioned`, error);
            return;
        }
        console.log('✅ UpdateRank.js functioned');

        interaction.reply(`You updated ${member} to ${Num} events attended`);
    },
};