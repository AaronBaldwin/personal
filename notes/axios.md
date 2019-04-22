# Axios
Axios is a node library to make HTTP requests.  It can be chained with promise like syntax.
`axios.post(`example.com/abcd`, {...body...}).then(() => {})`
Axios promises resolve for 2xx responses and reject for all 4xx responses
Axios provides a generic error message in the .catch() block by default
`.catch(err => console.log(err))`
^ will not return any information from the server itself about the error
`.catch(err => console.log(err.response))`
^ Does return data about the failure as specified by the server