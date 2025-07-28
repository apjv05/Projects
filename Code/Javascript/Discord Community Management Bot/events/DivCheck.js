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

        const Divs = new Map([
            ['GrandArmy', '1275982807801532416']
        ]);

        await AssignRole('Div', Divs, oldMember, newMember);
    }
}