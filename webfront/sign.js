document.getElementById('signForm').addEventListener('submit', function(e) {
    e.preventDefault();
    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;
    const privatekeypem = document.getElementById('privatekeypem').value;

    fetch('http://localhost:8080/sign', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({username, password,privatekeypem})
    })
        .then(response => response.json())
        .then(data => {
            if (data.sign) {
                document.getElementById('signDisplay').value = data.sign;
            } else {
                response.json().then(data => alert('sign failed: ' + data.error));
            }
        })
        .catch(error => console.error('Error:', error));
});
