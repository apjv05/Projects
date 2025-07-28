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

        const Activity = new Map([
            ['DM', '1392178622571483298'],
            ['Active', '1392176693225066689'],
            ['InactiveNotice', '1392176791371649175'],
            ['Retired', '1389701442746585108'],
            ['MIA', '1289380578436845568']
        ]);

        await AssignRole('Activity', Activity, oldMember, newMember);
    }
}