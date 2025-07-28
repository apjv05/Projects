const { SlashCommandBuilder } = require('discord.js');
const Motif = require('../../utils/commands/CommandVariables.js');
const { db } = require('../../data/db.js');
const path = require('path');

console.log(`${path.basename(__filename)} Loaded!`);

module.exports = {
	data: new SlashCommandBuilder()
	.setName('comms-check')
	.setDescription('check for a specified amount of users to dm')

    .addIntegerOption(option =>
    option.setName('number')
        .setDescription('how many users you want to contact')
        .setRequired(true))

    .addStringOption(option =>
            option.setName('game')
                .setDescription('the game you are DMing for')
                .setRequired(false)
                .addChoices(
                    { name: 'arcane-odyssey', value: 'ArcaneOdyssey' },
                    { name: 'deepwoken', value: 'Deepwoken' },
                    { name: 'the-wild-west', value: 'WildWest' },
                    { name: 'game-night', value: 'GameNight' },
                    { name: 'rogueblox', value: 'Rogueblox'}
                ))

    .addStringOption(option =>
            option.setName('div')
                .setDescription('division you are DMing for')
                .setRequired(false)
                .addChoices(
                    { name: 'grand-army', value: 'GrandArmy' }
                )),

	async execute(interaction) {
		const number = interaction.options.getInteger('number');
        const game = interaction.options.getString('game');
        const div = interaction.options.getString('div');
        let Message = `DM: `;

        
        if (number < 1) {
            console.error(`Input must be > 0`);
            await interaction.reply(`Input must be > 0`);
            return;
        }

        if (div && game) {
            const { data, error } = await db
                .from('member')
                .select('UserID')
                .eq('Div', div)
                .eq(game, true)
                .lte('LastAttendanceDate', Motif.Threshold)
                .lte('LastContactDate', Motif.Threshold)
                .eq('Activity', 'Active')
                .order('LastContactDate', {ascending: true})
                .limit(number);
            if(error) {
                console.error(`Error fetching member from db`);
                return;
            }
            Message += FormatMessage(data);
        } 
        else if (div) {
            const { data, error } = await db
                .from('member')
                .select('UserID')
                .eq('Div', div)
                .lte('LastAttendanceDate', Motif.Threshold)
                .lte('LastContactDate', Motif.Threshold)
                .order('LastContactDate', {ascending: true})
                .limit(number);
            console.log(div);
            if(error) {
                console.error(`Error fetching member from db`);
                return;
            }
            Message += FormatMessage(data);
        } 
        else if (game) {
            const { data, error } = await db
                .from('member')
                .select('UserID')
                .eq(game, true)
                .lte('LastAttendanceDate', Motif.Threshold)
                .lte('LastContactDate', Motif.Threshold)
                .eq('Activity', 'Active')
                .order('LastContactDate', {ascending: true})
                .limit(number);
            if(error) {
                console.error(`Error fetching member from db`);
                return;
            }
            Message += FormatMessage(data);
        }
        else {
            const { data, error } = await db
                .from('member')
                .select('UserID')
                .lte('LastAttendanceDate', Motif.Threshold)
                .lte('LastContactDate', Motif.Threshold)
                .eq('Activity', 'Active')
                .order('LastContactDate', {ascending: true})
                .limit(number);
            if(error) {
                console.error(`Error fetching member from db`);
                return;
            }
            Message += FormatMessage(data);
        }
        if (game && div) {
            Message += '\n Must DM: ';
            const { data, error } = await db
                .from('member')
                .select('UserID')
                .eq('Div', div)
                .eq(game, true)
                .eq('Activity', 'DM')
                .order('LastContactDate', {ascending: true})
            if(error) {
                console.error(`Error fetching member from db`);
                return;
            }
            Message += FormatMessage(data);
        } 
        else if (game) {
            Message += '\n Must DM: ';
            const { data, error } = await db
                .from('member')
                .select('UserID')
                .eq(game, true)
                .eq('Activity', 'DM')
                .order('LastContactDate', {ascending: true})
            if(error) {
                console.error(`Error fetching member from db`);
                return;
            }
            Message += FormatMessage(data);
        }
        console.log(Message);
        await interaction.reply(`${Message}`);
    }
}

//data: group of people that you want to add to the output message
//return val: all people from data processed into a string for the user to see
function FormatMessage(data) {
    let members = '';
    for(const member of data) {
        const memberID = member?.UserID;
        if (memberID) {
            members += `<@${memberID}> `;
            console.log(`${memberID} added to the message!`);
        }
        else {
            console.warn(`Member ID missing`, member);
            continue;
        }
        console.log(`Random member ${memberID} fetched`);
    }
    return members;
}