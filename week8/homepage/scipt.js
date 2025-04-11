// Dynamic greeting based on time of day
function updateGreeting() {
    const hour = new Date().getHours();
    let greeting;

    if (hour < 12) {
        greeting = "Good morning!";
    } else if (hour < 18) {
        greeting = "Good afternoon!";
    } else {
        greeting = "Good evening!";
    }

    const greetingElement = document.getElementById("greeting");
    if (greetingElement) {
        greetingElement.textContent = greeting;
    }
}

// Call greeting function when page loads
document.addEventListener("DOMContentLoaded", updateGreeting);

// Show message function for the learn more button
function showMessage() {
    alert("Thank you for your interest! Check out my projects page for more information.");
}

// Contact form validation
function validateForm(event) {
    event.preventDefault();
    const form = event.target;
    if (!form.checkValidity()) {
        event.stopPropagation();
        form.classList.add('was-validated');
        return false;
    }

    // Success handling
    const submitButton = form.querySelector('button[type="submit"]');
    submitButton.disabled = true;
    submitButton.innerHTML = '<span class="spinner-border spinner-border-sm" role="status" aria-hidden="true"></span> Sending...';

    setTimeout(() => {
        alert('Thank you for your message! I\'ll get back to you soon.');
        form.reset();
        form.classList.remove('was-validated');
        submitButton.disabled = false;
        submitButton.innerHTML = 'Send Message';
    }, 1000);

    return false;
}

// Add smooth scroll animation for project cards
document.addEventListener('DOMContentLoaded', function() {
    const projectCards = document.querySelectorAll('.project-card');

    const observer = new IntersectionObserver((entries) => {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                entry.target.style.opacity = '1';
                entry.target.style.transform = 'translateY(0)';
            }
        });
    }, { threshold: 0.1 });

    projectCards.forEach(card => {
        card.style.opacity = '0';
        card.style.transform = 'translateY(20px)';
        card.style.transition = 'all 0.5s ease-out';
        observer.observe(card);
    });
});

// Add skill bar animation
function animateSkillBars() {
    const progressBars = document.querySelectorAll('.progress-bar');
    progressBars.forEach(bar => {
        const width = bar.style.width;
        bar.style.width = '0';
        setTimeout(() => {
            bar.style.width = width;
        }, 200);
    });
}

// Initialize animations
document.addEventListener('DOMContentLoaded', function() {
    updateGreeting();
    animateSkillBars();
});

// Add scroll-based navbar behavior
window.addEventListener('scroll', function() {
    const navbar = document.querySelector('.navbar');
    if (window.scrollY > 50) {
        navbar.style.backgroundColor = 'rgba(33, 37, 41, 0.95)';
        navbar.style.boxShadow = '0 2px 10px rgba(0,0,0,0.1)';
    } else {
        navbar.style.backgroundColor = 'rgb(33, 37, 41)';
        navbar.style.boxShadow = 'none';
    }
});

// Enhanced animations for elements
document.addEventListener('DOMContentLoaded', function() {
    const animatedElements = document.querySelectorAll('.project-card, .skill-bar, .timeline-item');

    const observer = new IntersectionObserver((entries) => {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                entry.target.style.animation = 'fadeInUp 0.6s ease forwards';
                observer.unobserve(entry.target);
            }
        });
    }, { threshold: 0.1 });

    animatedElements.forEach(element => {
        observer.observe(element);
    });

    // Initialize Bootstrap tooltips
    const tooltipTriggerList = [].slice.call(document.querySelectorAll('[data-bs-toggle="tooltip"]'));
    tooltipTriggerList.map(function (tooltipTriggerEl) {
        return new bootstrap.Tooltip(tooltipTriggerEl);
    });
});
