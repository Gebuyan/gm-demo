document.getElementById('loginForm').addEventListener('submit', function(e) {
    e.preventDefault();
    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;
    const sign = document.getElementById('sign').value;
    fetch('http://localhost:8080/login', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({username, password,sign})
    })
        .then(response => response.json())
        .then(data => {
            if (data.message) {
                alert('Login successful');
            } else {
                alert('Login failed: ' + data.error);
            }
        })
        .catch(error => console.error('Error:', error));
});
