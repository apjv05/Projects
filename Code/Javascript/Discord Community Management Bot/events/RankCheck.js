const { Events } = require('discord.js');
const { AssignRole } = require('../utils/events/CheckForRole.js');
const Vars = require('../utils/events/MemberChecks');
const OldNew = require('../utils/events/OldNewMemberChecks');
const path = require('path');

console.log(`${path.basename(__filename)} Loaded!`);

module.exports = {
    name: Events.GuildMemberUpdate,
    async execute(oldMember, newMember) {
        const check = Vars(newMember);
        const OldNewCheck = OldNew(oldMember, newMember);
        if (!OldNewCheck.rolesChanged) return;
        if (check.IsBot) return;
        if (check.HasAlly) return;
        if (check.HasVisitor) return;
        if (check.HasDiplomat) return;
        if (check.HasForeigner) return;

        const Ranks = new Map([
            ['Arrival', '1392177116967080116'],
            ['Recruit', '1123032428462747763'],
            ['Militia', '1123031407728537701'],
            ['Squire', '1205337225030541384'],
            ['Knight', '1123030257872670850'],
            ['Captain', '1123027773477367888'],
            ['Lord', '1123002619766513674']
        ]);

       await AssignRole('Rank', Ranks, oldMember, newMember);
    }
}