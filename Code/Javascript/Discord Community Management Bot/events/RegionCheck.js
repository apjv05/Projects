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

        const Regions = new Map([
            ['NA', '1387526637003866304'],
            ['SA', '1387526694004588614'],
            ['ANZ', '1387526759729074176'],
            ['EU', '1387562690251329719'],
            ['APAC', '1387562768818769941'],
            ['MENA', '1387563041780142182']
        ]);

        await AssignRole('Region', Regions, oldMember, newMember);
    }
}