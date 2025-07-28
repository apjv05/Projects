const { Events } = require('discord.js');
const { db } = require('../data/db');
const Vars = require('../utils/events/MemberChecks');
const OldNew = require('../utils/events/OldNewMemberChecks');
const Motif = require('../utils/commands/CommandVariables');
const path = require('path');

console.log(`${path.basename(__filename)} Loaded!`);

module.exports = {
    name: Events.GuildMemberUpdate,
    async execute(oldMember, newMember) {
        const check = Vars(oldMember);
        const OldNewCheck = OldNew(oldMember, newMember);

        const CrossCav = '1123033790030299157';
        const HadRole = oldMember.roles.cache.has(CrossCav);
        const HasRole = newMember.roles.cache.has(CrossCav);

        if (HadRole) return;
        if (!OldNewCheck.rolesChanged) return;
        if (check.IsBot) return;
        if (check.HasAlly) return;
        if (check.HasVisitor) return;
        if (check.HasDiplomat) return;
        if (check.HasForeigner) return;
        
        if(!HadRole && HasRole) {
            try {
                const { error } = await db
                .from('member')
                .upsert({
                    'UserID': check.MemberID,
                    'LastAttendanceDate': Motif.Threshold,
                    'LastContactDate': Motif.Threshold,
                    'Rank': 'Arrival'
                });

                if(error) throw error;
                console.log(`${check.MemberName} has been added to the db!`);
            }
            catch (err) {
                console.error(`${check.MemberName} HAS NOT been added to the db`, err);
            }
        }
    }
}