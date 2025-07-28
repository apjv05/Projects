const { SlashCommandBuilder } = require('discord.js');
const { db } = require('../../data/db.js');
const path = require('path');

console.log(`${path.basename(__filename)} Loaded!`);

module.exports = {
    data: new SlashCommandBuilder()
        .setName('pull-info')
        .setDescription('Get info about a member!')
        .addUserOption(option =>
            option.setName('member')
                .setDescription(`The member you are getting info about`)
                .setRequired(true)
        ),
    async execute(interaction) {
        const member = interaction.options.getUser('member');
        let ContactPerson = ``;
          
        try {
            const { data, error } = await db
                .from('member')
                .select('*')
                .eq('UserID', member.id)
                .single();
            
            if (!data) {
                await interaction.reply(`No info found for ${member.username}.`);
                console.error('No data on user requested.');
                return;
            }
            if (error) throw error;
            if(data.LastContactPerson) ContactPerson = `<@${data.LastContactPerson}>`;

            const memberName = await interaction.client.users.fetch(member.id);
            let message = `User: ${memberName}\n`;
            message +=    `Division: ${data.Div || 'None'}\n`;
            message +=    `Rank: ${data.Rank || 'None'}\n`;
            message +=    `Plays Wild West: ${data.WildWest || 'false'}\n`;
            message +=    `Plays Arcane Odyssey: ${data.ArcaneOdyssey || 'false'}\n`;
            message +=    `Plays Deepwoken: ${data.Deepwoken || 'false'}\n`;
            message +=    `Plays Rogueblox: ${data.Rogueblox || 'false'}\n`;
            message +=    `Region: ${data.Region || 'N/A'}\n`;
            message +=    `Events Attended: ${data.EventsAttended}\n`;
            message +=    `Last Attendance Date: ${data.LastAttendanceDate || 'N/A'}\n`;
            message +=    `Last Contact Date: ${data.LastContactDate || 'N/A'}\n`;
            message +=    `Last Contact Person: ${ContactPerson || 'No one'}\n`;
            message +=    `Activity: ${data.Activity || 'N/A'}\n`;
            message +=    `Comment: ${data.Comments || ''}`;

            console.log('✅ PullInfo.js functioned');
            interaction.reply(`${message}`);
        }
        catch (err) {
            console.error('❌ PullInfo.js malfunctioned', err);
        }
        console.log('PullInfo.js executed');
    },
};