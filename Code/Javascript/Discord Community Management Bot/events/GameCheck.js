const { Events } = require('discord.js');
const { db } = require('../data/db');
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

        const games = new Map([
            ['ArcaneOdyssey', '1266097155421241498'],
            ['Deepwoken', '1266097152480776242'],
            ['WildWest', '1266097154087452743'],
            ['Rogueblox', '1266097150379429961']
        ]);

        //we don't use the function here because 
        //it uses the keys in the map as the column name
        //and its a boolean value instead of a string 
        //like all the files
        for(const [gameName, roleId] of games) {
            const HadRole = oldMember.roles.cache.has(roleId);
            const HasRole = newMember.roles.cache.has(roleId);

            if(HadRole && HasRole) continue;
            else if(!HadRole && !HasRole) continue;
            else if(!HadRole && HasRole) {
                try {
                    const { error } = await db
                    .from('member')
                    .update({ [gameName]: true })
                    .eq('UserID', check.MemberID);

                    if(error) throw error;
                    console.log(`${check.MemberName} now has ${gameName} role`);
                }
                catch (err) {
                    console.error(`${gameName} was not added to ${check.MemberName}`, err);
                }
                break;
            }
            else if(HadRole && !HasRole) {
                try {
                    const { error } = await db
                    .from('member')
                    .update({ [gameName]: false })
                    .eq('UserID', check.MemberID);

                    if(error) throw error;
                    console.log(`${gameName} has been removed from ${check.MemberName}`);
                }
                catch (err) {
                    console.error(`${gameName} was not removed from ${check.MemberName}`, err);
                }
                break;
            }
        }
    }
}