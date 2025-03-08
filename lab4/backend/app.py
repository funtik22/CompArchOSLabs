from flask import Flask, jsonify, request, make_response
from flask_cors import CORS
from flask_sqlalchemy import SQLAlchemy
from os import environ

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = environ.get('DB_URL')
CORS(app)
db = SQLAlchemy(app)

class User(db.Model):
    __tablename__ = 'users'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(80), unique=False, nullable=False)
    phone = db.Column(db.String(80), unique=True, nullable=False)
    note = db.Column(db.String(80), unique=True, nullable=False)

    def json(self):
        return {'id': self.id, 'name': self.name, 'phone': self.phone, 'note': self.note}

with app.app_context():
    db.create_all()

@app.route("/api/v1/users", methods=["GET"])
def get_users():
    try:    
        users = User.query.all()
        return make_response(jsonify([user.json() for user in users]), 200)    
    except Exception as e:
        return make_response(jsonify({'error': 'Failed to fetch users', 'details': str(e)}), 500)
    
@app.route("/api/v1/add", methods=["POST"])
def add_user():
    try:
        data = request.get_json()
        if not data:
            return make_response(jsonify({'error': 'Invalid JSON'}), 400)
        existing_user = User.query.filter_by(phone=data["phone"]).first()
        if existing_user:
            return make_response(jsonify({'error': 'User with this phone already exists'}), 400)
        new_user = User(name = data['name'], phone = data['phone'], note = data['note'])
        db.session.add(new_user)
        db.session.commit()
        return make_response(jsonify({'message': 'user created'}), 201)
    except Exception as e:
        return make_response(jsonify({'error': 'Failed to add user', 'details': str(e)}), 500)

@app.route("/api/v1/update", methods=["PUT"])
def update_user():
    try:
        data = request.get_json()

        if not data:
            return make_response(jsonify({'error': 'Invalid JSON'}), 400)

        user = None
        if "id" in data:
            user = User.query.get(data["id"])
        elif "phone" in data:
            user = User.query.filter_by(phone=data["phone"]).first()
        elif "name" in data:
            users = User.query.filter_by(name=data["name"]).all()
            if len(users) == 0:
                return make_response(jsonify({'error': 'User not found'}), 404)
            elif len(users) > 1:
                return make_response(jsonify({'error': 'Multiple users found. Please specify phone or id'}), 400)
            user = users[0]
        
        if "name" in data:
            user.name = data["name"]
        if "phone" in data:
            existing_user = User.query.filter_by(phone=data["phone"]).first()
            if existing_user and existing_user.id != user.id:
                return make_response(jsonify({'error': 'Phone number already in use'}), 400)
            user.phone = data["phone"]
        if "note" in data:
            user.note = data["note"] 

        db.session.commit()
        return make_response(jsonify({'message': 'User updated successfully'}), 200)
    
    except Exception as e:
        db.session.rollback()
        return make_response(jsonify({'error': 'Internal Server Error', 'details': str(e)}), 500)


@app.route("/api/v1/delete", methods=["DELETE"])
def delete_user():
    try:
        data = request.get_json()
        if not data:
            return make_response(jsonify({'error': 'Invalid JSON'}), 400)

        user = None

        if "id" in data:
            user = User.query.get(data["id"])
        
        elif "phone" in data:
            user = User.query.filter_by(phone=data["phone"]).first()

        elif "name" in data:
            users = User.query.filter_by(name=data["name"]).all()
            if len(users) == 0:
                return make_response(jsonify({'error': 'User not found'}), 404)
            elif len(users) > 1:
                return make_response(jsonify({'error': 'Multiple users found. Please specify phone or id'}), 400)
            user = users[0] 

        if not user:
            return make_response(jsonify({'error': 'User not found'}), 404)

        db.session.delete(user)
        db.session.commit()
        
        return make_response(jsonify({'message': 'User deleted successfully'}), 200)

    except Exception as e:
        db.session.rollback() 
        return make_response(jsonify({'error': 'Internal Server Error', 'details': str(e)}), 500)


if __name__ == "__main__":
    app.run(debug=True)