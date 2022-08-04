/* Use this as a template */

const data = "~/.ghostfs/root";
const host = "0.0.0.0";

module.exports = {
  apps: [
    {
      script: "./build/standalone/GhostFS",
      cwd: __dirname,
      watch: false,
      args: `--server --root ${data} --bind ${host}`,
    },
  ],
};
