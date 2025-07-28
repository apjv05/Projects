function OldNew(OldMember, newMember) {
    const oldRoles = OldMember.roles.cache;
    const newRoles = newMember.roles.cache;
    return {
        rolesChanged: oldRoles.size !== newRoles.size || [...oldRoles.keys()].some(role => !newRoles.has(role)),
    }
}

module.exports = OldNew;