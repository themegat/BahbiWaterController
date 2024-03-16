const admin = require('firebase-admin');
const serviceAccount = require('../private/service-account.json');

admin.initializeApp({
    credential: admin.credential.cert(serviceAccount),
});

const intervalRef = setInterval(deleteAnonymousUsers, 1001);

function deleteAnonymousUsers(nextPageToken) {
    admin
        .auth()
        .listUsers(20, nextPageToken)
        .then(function (listUsersResult) {
            listUsersResult.users.forEach(function (userRecord) {
                if (userRecord.providerData.length === 0) { 
                    console.log(userRecord); 
                    admin.auth().deleteUser(userRecord.uid)
                        .then(function () {
                            console.log("Successfully deleted user");
                        })
                        .catch(function (error) {
                            console.log("Error deleting user:", error);
                        });
                } else {
                    cleanup();
                }
            });
            if (listUsersResult.pageToken) {
                deleteAnonymousUsers(listUsersResult.pageToken);
            }
        })
        .catch(function (error) {
            console.log('Error listing users:', error);
        });
}

function cleanup() {
    clearInterval(intervalRef);
    console.log('finished');
    process.exit();
}