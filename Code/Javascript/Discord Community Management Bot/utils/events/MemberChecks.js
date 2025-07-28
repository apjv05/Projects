function Vars(member) {
    return {
        HasAlly: member.roles.cache.has(1196238663009452143), //Ally
        HasVisitor: member.roles.cache.has(1252412464134361199), //Visitor
        HasDiplomat: member.roles.cache.has(1123035907193307316), //Foreign Diplomat
        HasForeigner: member.roles.cache.has(1123037220643815424), //Foreigner
        IsBot: member.user.bot,
        MemberID: member.user.id,
        MemberName: member.user.username,
    };
}

module.exports = Vars;