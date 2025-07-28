const { SlashCommandBuilder } = require('discord.js');
const { db } = require('../../data/db.js');
const Motif = require('../../utils/commands/CommandVariables.js');
const path = require('path');

console.log(`${path.basename(__filename)} Loaded!`);

module.exports = {
    data: new SlashCommandBuilder()
        .setName('host')
        .setDescription('create and log your event automatically.')
        .addStringOption(option =>
            option.setName('title')
                .setDescription('name of your event')
                .setRequired(true))
        .addStringOption(option =>
            option.setName('attendees')
                .setDescription('mention users who attended (@user1 @user2)')
                .setRequired(true))
        .addStringOption(option =>
            option.setName('co-hosts')
                .setDescription('people who helped you host')
                .setRequired(false))
        .addStringOption(option =>
            option.setName('visitors')
                .setDescription('people who were in vc, but didnt join the event')
                .setRequired(false))
        .addAttachmentOption(option =>
            option.setName('image')
                .setDescription('add a picture from the event')
                .setRequired(false))
        .addStringOption(option =>
            option.setName('image-url')
                .setDescription('add a picture url from the event')
                .setRequired(false))
        .addStringOption(option =>
            option.setName('notes')
                .setDescription('any extra information you would like to add')
                .setRequired(false)),

    async execute(interaction) {
        const Title = interaction.options.getString('title');
        const Host = interaction.user.id;
        const CoHost = interaction.options.getString('co-hosts');
        const Attendees = interaction.options.getString('attendees');
        const Visitors = interaction.options.getString('visitors');
        const Notes = interaction.options.getString('notes');
        const Image = interaction.options.getAttachment('image');
        const ImageURL = interaction.options.getString('image-url');
        let People = new Set([Host]);

        let EventMessage = `${Title}\nHost: <@${Host}>\n`;

        if (CoHost) {
            EventMessage += `Co-Hosts: `;
            EventMessage = CountPeople(CoHost, EventMessage, People);
        }

        //attendees
        EventMessage += 'Attendees: ';
        EventMessage = CountPeople(Attendees, EventMessage, People);

        if (Visitors) {
            EventMessage += `Visitors: `;
            EventMessage = CountPeople(Visitors, EventMessage);
        }

        if (Notes) EventMessage += `${Notes}\n`;
        if (Image) EventMessage += `\n${Image.url}`;
        if (ImageURL) EventMessage += `\n${ImageURL}`;

        await interaction.reply({ content: EventMessage });

        try {
            let Promotions = ``;
            let PromotedPeople = 0;

            for (const user of People) {
                const member = await interaction.guild.members.fetch(user);
                const { data, error } = await db
                    .from('member')
                    .select('EventsAttended')
                    .eq('UserID', user)
                    .single();
                console.log(user);
                if (error) {
                    console.error('Error fetching member:', error);
                    continue;
                }

                if(data.EventsAttended + 1 == 7) {
                    Promotions += await handlePromotion(interaction, user, member, data.EventsAttended + 1);
                    PromotedPeople++;
                }
                else if(data.EventsAttended + 1 == 3) {
                    Promotions += await handlePromotion(interaction, user, member, data.EventsAttended + 1);
                    PromotedPeople++;
                }
                else if(data.EventsAttended + 1 == 1) {
                    Promotions += await handlePromotion(interaction, user, member, data.EventsAttended + 1);
                    PromotedPeople++;
                }

                const { error: updateError } = await db
                    .from('member')
                    .update({
                        EventsAttended: (data?.EventsAttended || 0) + 1,
                        LastAttendanceDate: Motif.Today
                    })
                    .eq('UserID', user);

                if (updateError) console.error('Error updating member:', updateError);
                else console.log(`${member.displayName} updated successfully`);
            }

            if(PromotedPeople > 1) await interaction.user.send(`${Promotions}have all been promoted`);
            else if (PromotedPeople == 1) await interaction.user.send(`${Promotions}has been promoted`);

            console.log('Event hosted successfully!');
        } 
        catch (err) {
            console.error('Error in host command:', err);
        }
    }
};

//people: user inputted group from the / command
//msg: message you want to add to your existing message
//set: set used to track amount of attendees
//return val: message added
function CountPeople(people, msg, set) {
    const userMentionRegex = /<@!?(\d+)>/g;
    let match;
    while ((match = userMentionRegex.exec(people)) !== null) {
        const userId = match[1];
        if(set) set.add(userId);
        msg += `<@${userId}> `;
    }
    msg += `\n`;
    return msg;
}

//userId: id of the user being promoted
//member: username of the user being promoted
//eventsAttended: number of events the user attended
//return val: adds @userid to the message
async function handlePromotion(interaction, userId, member, eventsAttended) {
    const Arrival = interaction.guild.roles.cache.get('1392177116967080116');
    const Recruit = interaction.guild.roles.cache.get('1123032428462747763');
    const Militia = interaction.guild.roles.cache.get('1123031407728537701');
    const Squire = interaction.guild.roles.cache.get('1205337225030541384');

    const promotionMap = {
        1: { rank: 'Recruit', add: Recruit, remove: Arrival },
        3: { rank: 'Militia', add: Militia, remove: Recruit },
        7: { rank: 'Squire', add: Squire, remove: Militia }
    };
    const promotion = promotionMap[eventsAttended];
    const { rank, add, remove } = promotion;

    const { error } = await db
        .from('member')
        .update({ Rank: rank })
        .eq('UserID', userId);

    if (error) console.error(`Failed to promote ${userId} to ${rank}`, error);

    if (remove) await member.roles.remove(remove);
    if (add) await member.roles.add(add);

    return `<@${userId}> `;
}