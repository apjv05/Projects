# Community Management Bot
A utility Discord bot designed to help faction leaders manage user information, automate role-based tracking, and streamline communication. This bot was specifically made for a group I am apart of, but with some work could be expanded and generalized for many different groups.

# Features
### Automatic Member Tracking
Creates and maintains a database of users triggered by
- Joining the server
  - Members are added to the database when then get the Cross Calvary Role
- Role Changes
  - Includes game roles, division roles, and region roles
- leaving the server
  - Members are deleted from the database once they leave

### CommsCheck
A command used to figure out who to DM that hasn't been active.

- Returns X random users who:
  - Have no attendance or contact in over a month
  - Have the Cross Cavalry role
  - Do not have the MIA role & Retired role
- the user gets prompted with optional division and game filters
- The user then has to run the log-user command to update the last time they were contacted

### HostEvent
Command used to create and log who hosted and attended an event. Updates the respective dates and logs total events for each user. If a user meets the requirements for rank up, it updates their database column to the next rank, updates their discord role to the next rank, and lets the host know who has been promoted.

### LogContact
Updates the last contact of a user to the current date and logs who contacted them.

### Manual Override
Added several commands to manually update user information in the database including comments, events attended, rank and deletion from the database.

### PullUserInfo
Shows all information in the database about a certain user.

# Database

### Member Table
Attribute | Type | Description
--------- | ---- | ----------
UserID | Automatic | ID discord assigned the user
Division | Automatic | Which division the member is in
Rank | Automatic | Rank that the member is
Games | Automatic | Games the member plays
Region | Automatic | Region the member lives in
EventsAttended | Semi-Automatic | Incremented for each event attended from the host command
Last Attendance | Semi-Automatic | Last time the user attended an event
Last Contact | Semi-Automatic | Last time the user was DMed
LastContactPerson | Semi-Automatic | Whoever last DM'ed the member's UserID
Comments | Manual | Notes about the user

# Tech Stack
- Javascript
- Node.js
- Discord.js API
- PostgreSQL
- Supabase

# How to run
  1. run `npm install discord.js` in the terminal to get all the packages you need.
  2. Deploy all commands with `node dc` in the terminal.
  3. Invite the bot to your server.
  4. run `node .` in the terminal to start the bot.

  # Notes
  - AI was only used to fill gaps in knowledge and help decipher errors/bugs