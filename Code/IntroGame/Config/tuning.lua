-- This file is used for tuning variables.
-- The engine can reload this file if it changes during the game (so you can
--  edit it and see changes in real-time).
--

BouncePeriod = {
  type = "float",   -- Supported types are int, float, string, and vector
  value = 2.0,      -- The engine will do it's darndest to parse whatever 
                    --  you put here
  readonly = false, -- By setting this to true (or "1", or "yes," etc.), 
                    --  you guard this variable. When SaveTuningVariables() 
                    --  is called, its value will remain unchanged. 
}
