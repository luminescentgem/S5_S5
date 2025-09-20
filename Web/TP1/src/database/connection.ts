import sqlite3 from 'sqlite3'

const DATABASE_PATH = '/tmp/tp_web/database.db'

class Database {
  private static instance: Database; // Private static variable to hold the singleton instance
  public db: sqlite3.Database;

  // Private constructor to enforce singleton
  constructor() {
    if (Database.instance) {
      throw new Error('Use Database.getInstance() to access the singleton instance.')
    }

    this.db = new sqlite3.Database(DATABASE_PATH, (err) => {
      if (err) {
        console.error('Error connecting to SQLite:', err)
      } else {
        console.log('Connected to SQLite database.')
      }
    })

    Database.instance = this
  }

  /**
   * Get the singleton instance of the Database.
   * @returns {Database} The singleton instance.
   */
  static getInstance() {
    if (!Database.instance) {
      new Database() // Initialize the singleton
    }
    return Database.instance
  }

  /**
   * Get the database connection object.
   * @returns {sqlite3.Database} The SQLite3 database instance.
   */
  async getDb() {
    if (!this.db) {
      throw new Error('Database is not initialized.')
    }
    return this.db
  }

  /**
   * Close the database connection.
   */
  async close() {
    if (this.db) {
      this.db.close((err) => {
        if (err) {
          console.error('Error closing SQLite connection:', err)
        } else {
          console.log('SQLite connection closed.')
        }
      })
    } else {
      console.warn('No SQLite connection to close.')
    }
  }
}

export default Database.getInstance()
