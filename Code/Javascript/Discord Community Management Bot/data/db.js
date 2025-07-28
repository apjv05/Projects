const { createClient } = require('@supabase/supabase-js');
const { supabaseUrl } = require('../config.json');
const { supabaseKey } = require('../config.json');
const db = createClient(supabaseUrl, supabaseKey);

async function testConnection() {
  try {
    const { err } = await db
    .from('member')
    .select('count', {count: 'exact', head: true });
    if (err) {
      console.log('supabase connection has failed', err);
      return false;
    }
    console.log('Supabase connection succeeded');
    return true;
  } catch(err) {
    console.log('supabase connection error: ', err.message);
    return false;
  }
}

module.exports = { db, testConnection };
