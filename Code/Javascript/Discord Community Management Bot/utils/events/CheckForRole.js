const { db } = require('../../data/db.js');
const Vars = require('./MemberChecks.js');

//oldMember: oldMember variable passed in the event
//Map: Hash Map that holds all the Role Names and IDs
//Role: Role you are checking to exclude
//Purpose: Check if your member has any other roles in the map besides the one that you passed
function CheckOther(oldMember, Map, Role) {
    for (const [RoleName, RoleID] of Map) {
        const HadRole = oldMember.roles.cache.has(RoleID);
        if(Role != RoleID && HadRole) return false;
    }
    return true;
};

//Column: Name of the column you want to change in supabase
//Map: Hash Map that holds all the Role Names and IDs
//oldMember: oldMember variable passed in the event
//newMember: newMember variable passed in the event
//Purpose: update the member's data in supabase to match their roles on discord
async function AssignRole(Column, Map, oldMember, newMember) {
    const check = Vars(newMember);

    for(const [Name, ID] of Map)  {
        const HadRole = oldMember.roles.cache.has(ID);
        const HasRole = newMember.roles.cache.has(ID);
            
        if(HadRole && HasRole) continue;
        else if(!HadRole && !HasRole) continue;
        else if(!HadRole && HasRole) {
            try {
                const { error } = await db
                .from('member')
                .update({ [Column] : Name })
                .eq('UserID', check.MemberID);

                if(error) throw error;
                console.log(`${check.MemberName} now has ${Name} role`);
            }
            catch (err) {
                console.error(`${Name} was not added to ${check.MemberName}`, err);
            }
            break;
        }
        else if(HadRole && !HasRole && CheckOther(oldMember, Map, ID)) {
            try {
                const { error } = await db
                .from('member')
                .update({ [Column] : 'None' })
                .eq('UserID', check.MemberID);

                if(error) throw error;
                console.log(`${Name} has been removed from ${check.MemberName}`);
            }
            catch (err) {
                console.error(`${Name} was not removed from ${check.MemberName}:`, err);
            }
            break;
        }
    }
}

module.export = AssignRole;