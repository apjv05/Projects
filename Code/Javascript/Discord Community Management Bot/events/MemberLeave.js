const { Events } = require('discord.js');
const { db } = require('../data/db');
const Vars = require('../utils/events/MemberChecks');
const path = require('path');

console.log(`${path.basename(__filename)} Loaded!`);

module.exports = {
    name: Events.GuildMemberRemove,
    async execute(member) {
        const check = Vars(member);
        if (check.IsBot) return;

        const MemberID = member.user.id;
        try {
            const { error } = await db
                .from('member')
                .delete()
                .eq('UserID', MemberID);

            if (error) throw error;
            console.log(`${check.MemberName} left the server & their row has been deleted`);
        } catch (err) {
            console.error(`${check.MemberName} left the server & their row HAS NOT been deleted`, err);
        }
    }
}