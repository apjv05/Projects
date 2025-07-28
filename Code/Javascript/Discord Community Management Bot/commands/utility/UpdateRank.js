const { SlashCommandBuilder } = require('discord.js');
const { db } = require('../../data/db');
const path = require('path');

console.log(`${path.basename(__filename)} Loaded!`);

module.exports = {
    data: new SlashCommandBuilder()
        .setName('update-rank')
        .setDescription('change a users rank')
        .addUserOption(option =>
            option.setName('member')
                .setDescription(`The member you are changing`)
                .setRequired(true)
        )
        .addStringOption(option =>
            option.setName('rank')
                .setDescription('rank you want the member to be')
                .setRequired(true)
                .addChoices(
                    { name: 'Arrival', value: 'Arrival' },
                    { name: 'Recruit', value: 'Recruit' },
                    { name: 'Militia', value: 'Militia' },
                    { name: 'Squire', value: 'Squire' },
                    { name: 'Knight', value: 'Knight' },
                    { name: 'Captain', value: 'Captain'},
                    { name: 'Lord', value: 'Lord'}
                )),
    async execute(interaction) {
        const member = interaction.options.getUser('member');
        const memberid = member.id;
        const Rank = interaction.options.getString('rank');
        const { error } = await db
            .from('member')
            .update({'Rank': Rank})
            .eq('UserID', memberid);

        if (error) {
            console.error(`❌ UpdateRank.js malfunctioned`, error);
            return;
        }
        console.log('✅ UpdateRank.js functioned');

        interaction.reply(`You updated ${member} to ${Rank}`);
    },
};